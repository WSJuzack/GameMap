using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResetButton : MonoBehaviour
{
    public void OnClick() {
        var Gameobjects = GameObject.FindGameObjectsWithTag("DrawnLine");
        for (int i = 0 ; i< Gameobjects.Length; i++) {
            Destroy(Gameobjects[i]);
        }
    }
}
