using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Light
    {
        private const int Id = 8;
        private float[] m_Color = {255, 255, 255, 1};
        private float[] m_Extra = {0, 0, 0, 0};
        private int m_LightType;
        private bool m_added;

        public override string ToString() { return "Light"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public float[] GetColor() { return m_Color; }
        public float[] GetExtra() { return m_Extra; }
        public int GetLightType() { return m_LightType; }
        public int GetId() { return Id; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetColor(float r, float g, float b, float a)
        {
            m_Color[0] = r;
            m_Color[1] = g;
            m_Color[2] = b;
            m_Color[3] = a;
        }
        public void SetExtra(float x, float y, float z, float w)
        {
            m_Extra[0] = x;
            m_Extra[1] = y;
            m_Extra[2] = z;
            m_Extra[3] = w;
        }
        public void SetLightType(int type) { m_LightType = type; }
    }
}
