using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeColor : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        objectRenderer.material.SetColor("_Color", Random.ColorHSV());
    }

    // Update is called once per frame
    void Update()
    {
        float deltaTime = Time.deltaTime;
        Color oldColor = objectRenderer.material.GetColor("_Color");
        Color newColor = new Color(oldColor.r + deltaTime, oldColor.g + Time.deltaTime, oldColor.b + Time.deltaTime);

        if (newColor.r > 1.0f)
            newColor.r = 0.0f;
        if (newColor.g > 1.0f)
            newColor.g = 0.0f;
        if (newColor.b > 1.0f)
            newColor.b = 0.0f;

        objectRenderer.material.SetColor("_Color", newColor); 
    }

    public Renderer objectRenderer;
}
