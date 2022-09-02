using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.UI;

public class ChangeTexture : MonoBehaviour
{
    public Image image;
    public void changeTexture()
    {
        string path = "Assets/TempHeightmaps/000.png";
        AssetDatabase.Refresh();
        Texture2D tex = AssetDatabase.LoadAssetAtPath<Texture2D>(path);
        Sprite sprite = Sprite.Create(tex, new Rect(0.0f, 0.0f, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100.0f);
        image.sprite = sprite;
        image.gameObject.SetActive(true);
    }
}
