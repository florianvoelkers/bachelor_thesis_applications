using System;
using Unity.Entities;

[Serializable]
public struct MovementSpeed : IComponentData
{
    public float Value;
}
