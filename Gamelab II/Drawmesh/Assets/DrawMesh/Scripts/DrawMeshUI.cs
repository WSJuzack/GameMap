using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using CodeMonkey.Utils;

public class DrawMeshUI : MonoBehaviour {

    private void Awake() {
        transform.Find("Thickness1Btn").GetComponent<Button>().onClick.AddListener(() => { SetThickness(0.2f); });
        transform.Find("Thickness2Btn").GetComponent<Button>().onClick.AddListener(() => { SetThickness(0.6f); });
        transform.Find("Thickness3Btn").GetComponent<Button>().onClick.AddListener(() => { SetThickness(1.0f); });
        transform.Find("Thickness4Btn").GetComponent<Button>().onClick.AddListener(() => { SetThickness(2.0f); });

        transform.Find("Color1Btn").GetComponent<Button>().onClick.AddListener(() => { SetColor(UtilsClass.GetColorFromString("323232")); });
        transform.Find("Color2Btn").GetComponent<Button>().onClick.AddListener(() => { SetColor(UtilsClass.GetColorFromString("646464")); });
        transform.Find("Color3Btn").GetComponent<Button>().onClick.AddListener(() => { SetColor(UtilsClass.GetColorFromString("969696")); });
        transform.Find("Color4Btn").GetComponent<Button>().onClick.AddListener(() => { SetColor(UtilsClass.GetColorFromString("C8C8C8")); });
        transform.Find("Color5Btn").GetComponent<Button>().onClick.AddListener(() => { SetColor(UtilsClass.GetColorFromString("FFFFFF")); });
    }

    private void SetThickness(float thickness) {
        DrawMeshFull.Instance.SetThickness(thickness);
    }

    private void SetColor(Color color) {
        DrawMeshFull.Instance.SetColor(color);
    }

}