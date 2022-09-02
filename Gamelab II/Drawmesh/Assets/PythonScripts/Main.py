import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import abc
from PIL import Image
from numpy import asarray
import numpy as np
import os
import UnityEngine as ue


# ------------------------------------------ everything here, because import in Unity not working ------------- #
class DataAccess:
    dir_name = os.path.realpath('..')
    data_path = os.path.join(dir_name, 'Data/')

    @staticmethod
    def save_img(path, img):
        Image.fromarray(np.uint8(img)).save(DataAccess.data_path + path)

    @staticmethod
    def load_img(path):
        img = Image.open(DataAccess.data_path + path).convert('L')
        return asarray(img)

    @staticmethod
    def get_path(path):
        return DataAccess.data_path + path


class NeuralNetwork:
    def __init__(self, size_x, size_y, model_path=""):
        self.model = None
        self.size_x = size_x
        self.size_y = size_y
        self.model_path = model_path

    @abc.abstractmethod
    def set_up_model(self):
        """Should return a keras Sequential model"""
        return

    def load_saved_model(self):
        if self.model_path == "":
            print("Error! No path to saved model given!")
            return
        self.model.load_weights(DataAccess.get_path(self.model_path))

    def save_model(self):
        if self.model_path == "":
            print("Error! Can't save model! No path to save model given!")
            return
        print("Do you wish to overwrite the loaded model, with the newly trained model (y/n)?")
        while 1:
            answer = input()
            if answer.lower() == "y" or answer.lower() == "yes":
                self.model.save_weights(DataAccess.get_path(self.model_path))
                return
            elif answer.lower() == "n" or answer.lower() == "no":
                return
            else:
                print("Please input 'y' or 'n'")


class Generator(NeuralNetwork):
    def __init__(self, size_x, size_y, model_path=""):
        NeuralNetwork.__init__(self, size_x, size_y, model_path)
        self.set_up_model()

    def set_up_model(self):
        self.model = keras.Sequential(
            [
                keras.Input(shape=(self.size_x, self.size_y, 1)),
                layers.Conv2D(128, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(64, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(32, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2DTranspose(32, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2DTranspose(32, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2DTranspose(16, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(1, (4, 4), strides=(1, 1), padding="same", activation="sigmoid"),
            ],
            name="generator",
        )


class Dataprovider:
    def __init__(self, real_img_path, real_img_size, input_img_path, input_img_size, batch_size, test_img_path):
        self.sketch_path = os.path.realpath('') + "/Assets/HeightmapSketches/"
        print(self.sketch_path)
        self.real_img_size = real_img_size
        self.input_img_size = input_img_size
        self.batch_size = batch_size

    def load_sketches(self):
        img = Image.open(self.sketch_path + "Sketch.png").convert('L')
        img.resize(self.input_img_size, Image.ANTIALIAS)
        img.save(self.sketch_path + "Sketch.png")
        data_set = keras.preprocessing.image_dataset_from_directory(
            self.sketch_path, label_mode=None, image_size=self.input_img_size, batch_size=100, shuffle=False,
            color_mode="grayscale",
        ).map(lambda x: x / 255.0)
        for e in data_set:
            return e


class UNetGenerator(NeuralNetwork):
    def __init__(self, size_x, size_y, model_path=""):
        NeuralNetwork.__init__(self, size_x, size_y, model_path)
        self.set_up_model()

    def set_up_model(self):
        self.model = keras.Sequential(
            [
                keras.Input(shape=(self.size_x, self.size_y, 1)),

                # Contraction
                # layers.Conv2D(32, (3, 3), padding="same", activation="relu"),
                # layers.Conv2D(32, (3, 3), padding="same", activation="relu"),
                # layers.MaxPool2D((2, 2), strides=(2, 2)),
                layers.Conv2D(64, (3, 3), padding="same", activation="relu"),
                layers.Conv2D(64, (3, 3), padding="same", activation="relu"),
                layers.MaxPool2D((2, 2), strides=(2, 2)),
                # layers.Conv2D(128, (3, 3), padding="valid", activation="relu"),
                # layers.Conv2D(128, (3, 3), padding="valid", activation="relu"),
                # layers.MaxPool2D((2, 2), strides=(2, 2)),

                # Bottom Line
                layers.Conv2D(128, (3, 3), padding="same", activation="relu"),
                layers.Conv2D(128, (3, 3), padding="same", activation="relu"),

                # Expansion
                layers.Conv2DTranspose(64, (4, 4), strides=(2, 2), padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(64, (3, 3), padding="same", activation="relu"),
                layers.Conv2D(64, (3, 3), padding="same", activation="relu"),
                # layers.Conv2DTranspose(32, (4, 4), strides=(2, 2), padding="same"),
                # layers.LeakyReLU(alpha=0.2),

                layers.Conv2D(1, (2, 2), strides=(1, 1), padding="same", activation="sigmoid"),
            ],
            name="generator",
        )


output_x = 128
output_y = 128

input_x = 128
input_y = 128

batch_size = 32

real_img_path = DataAccess.get_path("128x128_Maps/")
input_img_path = DataAccess.get_path("128x128_Gestaffelt/")
test_img_path = DataAccess.get_path("drawn_test_imgs/")

dataprovider = Dataprovider(real_img_path=real_img_path, real_img_size=(output_x, output_y),
                            input_img_path=input_img_path, input_img_size=(input_x, input_y),
                            batch_size=batch_size, test_img_path=test_img_path)

generator = Generator(input_x, input_y, "model_gen2_zwischenspeicher/03/")


def generateImg(generator, dataprovider):
    input_images = dataprovider.load_sketches()
    generated_images = generator(input_images)
    generated_images *= 255
    generated_images.numpy()

    for i in range(0, generated_images.shape[0]):
        img = keras.preprocessing.image.array_to_img(generated_images[i])
        img.save(os.path.realpath("") + "/Assets/TempHeightmaps/%03d.png" % i)
    ue.Debug.Log("Done")


mode = 0

if mode == 0:
    generator.load_saved_model()
    generateImg(generator=generator.model, dataprovider=dataprovider)

