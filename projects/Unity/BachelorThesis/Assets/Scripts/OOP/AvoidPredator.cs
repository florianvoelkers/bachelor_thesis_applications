using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AvoidPredator : MonoBehaviour
{       
    [SerializeField] private float avoidDistanceX;
    [SerializeField] private float avoidDistanceY;

    private bool avoiding;
    private bool avoidingUp;
    private GameObject predator;

    private void Start()
    {
        predator = GameObject.Find("Predator");
    }

    // Update is called once per frame
    void Update()
    {
        float deltaTime = Time.deltaTime;
        
        float actualDistanceX = Mathf.Abs(gameObject.transform.position.x - predator.transform.position.x);
        float actualDistanceY = gameObject.transform.position.y - predator.transform.position.y;
        if (actualDistanceX < avoidDistanceX && Mathf.Abs(actualDistanceY) < avoidDistanceY)
        {
            avoiding = true;
            if (actualDistanceY >= 0.0f)
            {
                gameObject.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position. y + avoidDistanceY, gameObject.transform.position.z);
                avoidingUp = true;
            }
            else
            {
                gameObject.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y - avoidDistanceY, gameObject.transform.position.z);
                avoidingUp = false;
            }
        }

        if (actualDistanceX > avoidDistanceX && Mathf.Abs(actualDistanceY) < avoidDistanceY * 2 && avoiding)
        {
            if (avoidingUp)
                gameObject.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y - avoidDistanceY, gameObject.transform.position.z);
            else
                gameObject.transform.position = new Vector3(gameObject.transform.position.x, gameObject.transform.position.y + avoidDistanceY, gameObject.transform.position.z);

            avoiding = false;
        }
    }

    
}
