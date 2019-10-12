using System;
using Unity.Entities;

[Serializable]
public struct AvoidPredatorComponent : IComponentData
{
    public bool avoiding;
    public bool avoidingUp;
}

