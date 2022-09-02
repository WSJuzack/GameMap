using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;
//using CallPythonCode;

public class PNGSaver : MonoBehaviour {

    public GameObject RenderButton;
    public GameObject SaveHeightmap;
    public GameObject Input;
    public ChangeTexture texChanger;

    public CallPythonCode script;

    public void OnClick() {
            //ScreenCapture.CaptureScreenshot("GameScreenshot.png");
            StartCoroutine(CoroutineScreenshot());
            RenderButton.SetActive(true);
            SaveHeightmap.SetActive(true);
            Input.SetActive(true);
    }

    private IEnumerator CoroutineScreenshot() {
        yield return new WaitForEndOfFrame();

        int width = Screen.height;
        int height = Screen.height;
        Texture2D screenshotTexture = new Texture2D(width, height, TextureFormat.ARGB32, false);
        Rect rect = new Rect(0, 0, width, height);
        screenshotTexture.ReadPixels(rect, 0, 0);
        screenshotTexture.Apply();

        byte[] byteArray = screenshotTexture.EncodeToPNG();
        System.IO.File.WriteAllBytes(Application.dataPath + "/HeightmapSketches/Sketch.png", byteArray);
        script.callPython();
        yield return new WaitForSeconds(2);
        texChanger.changeTexture();
    }

}