using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class MessageHandler : MonoBehaviour
{
    public TextMeshProUGUI text;
    private int activeCounter = 0;
    public IEnumerator showMessage(string message)
    {
        text.text = message;
        text.gameObject.SetActive(true);
        activeCounter += 1;
        yield return new WaitForSeconds(3);
        activeCounter -= 1;
        if(activeCounter <= 0)
        {
            text.gameObject.SetActive(false);
        }
    }
}
