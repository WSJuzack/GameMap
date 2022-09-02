from tensorflow import keras
from tensorflow.keras import layers
from NeuralNetwork import NeuralNetwork


class Discriminator(NeuralNetwork):
    def __init__(self, size_x, size_y, model_path=""):
        NeuralNetwork.__init__(self, size_x, size_y, model_path)
        self.set_up_model()

    def set_up_model(self):
        self.model = keras.Sequential(
            [
                keras.Input(shape=(self.size_x, self.size_y, 1)),
                layers.Conv2D(32, kernel_size=4, strides=2, padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(64, kernel_size=4, strides=2, padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Conv2D(64, kernel_size=4, strides=2, padding="same"),
                layers.LeakyReLU(alpha=0.2),
                layers.Flatten(),
                layers.Dropout(0.2),
                layers.Dense(1, activation="sigmoid"),
            ],
            name="discriminator",
        )

