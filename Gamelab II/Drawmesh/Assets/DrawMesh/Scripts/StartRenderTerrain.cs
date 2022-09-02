using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartRenderTerrain : MonoBehaviour
{
    public void OnClick()
    {
        SceneManager.LoadScene("3D");
    }
}
