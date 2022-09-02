using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Position : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
      transform.position = new Vector3(Screen.height + 26, 0, 0);
    }

    
}
