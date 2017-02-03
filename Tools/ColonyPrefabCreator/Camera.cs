using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Camera
    {
        private const int Id = 4;
        private float m_FarPlane;
        private float m_NearPlane;
        float m_FOV;
        bool m_added;

        public override string ToString() { return "Camera"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public float GetFarPlane() { return m_FarPlane; }
        public float GetNearPlane() { return m_NearPlane; }
        public float GetFOV() { return m_FOV; }
        public int GetId() { return Id; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetFarPlane(float farPlane) { m_FarPlane = farPlane; }
        public void SetNearPlane(float nearPlane) { m_NearPlane = nearPlane; }
        public void SetFOV(float fov) { m_FOV = fov; }
    }
}
