using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveSideways : MonoBehaviour
{
    [SerializeField] private float minimumMovementSpeed = 2.0f;
    [SerializeField] private float maximumMovementSpeed = 10.0f;

    [SerializeField] private float movementSpeed;

    private void Start()
    {
        movementSpeed = Random.Range(minimumMovementSpeed, maximumMovementSpeed);
    }

    private void Update()
    {
        Vector3 oldPosition = transform.position;
        if (movementSpeed > 0.0f)
        {
            if (oldPosition.x < DemoManagerOOP.rightBound)
            {
                float newX = oldPosition.x + Time.deltaTime * movementSpeed;
                transform.position = new Vector3(newX, oldPosition.y, oldPosition.z);
            }
            else
            {
                float randomY = UnityEngine.Random.Range(DemoManagerOOP.bottomBound, DemoManagerOOP.topBound + 1.0f);
                transform.position = new Vector3(DemoManagerOOP.leftBound, randomY, oldPosition.z);
            }
        }
        else
        {
            if (oldPosition.x > DemoManagerOOP.leftBound)
            {
                float newX = oldPosition.x + Time.deltaTime * movementSpeed;
                transform.position = new Vector3(newX, oldPosition.y, oldPosition.z);
            }
            else
            {
                float randomY = UnityEngine.Random.Range(DemoManagerOOP.bottomBound, DemoManagerOOP.topBound + 1.0f);
                transform.position = new Vector3(DemoManagerOOP.rightBound, randomY, oldPosition.z);
            }
        }
        
    }
}
