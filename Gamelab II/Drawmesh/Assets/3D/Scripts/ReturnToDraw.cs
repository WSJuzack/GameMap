using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ReturnToDraw : MonoBehaviour
{
    public void OnClick()
    {
        SceneManager.LoadScene("DrawMeshFull");
    }
}
