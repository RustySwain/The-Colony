using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Transform
    {
        private float[] m_LocalPosition = {0, 0, 0, 0};
        private float[] m_LocalRotation = {0, 0, 0, 0};
        private float m_Scale;
        private bool m_added;

        public override string ToString() { return "Transform"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public float[] GetPosition() { return m_LocalPosition; }
        public float[] GetRotation() { return m_LocalRotation; }
        public float GetScale() { return m_Scale; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetPosition(float x, float y, float z)
        {
            m_LocalPosition[0] = x;
            m_LocalPosition[1] = y;
            m_LocalPosition[2] = z;
        }
        public void SetRotation(float x, float y, float z)
        {
            m_LocalRotation[0] = x;
            m_LocalRotation[1] = y;
            m_LocalRotation[2] = z;
        }
        public void SetScale(float scale) { m_Scale = scale; }
    }
}
