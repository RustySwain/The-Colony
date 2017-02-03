using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class GameObject
    {
        private int m_Id;
        private string m_Name = "Unnamed";
        private string m_Tag = "Untagged";
        private bool m_Transparent;
        private bool m_Dynamic;

        public override string ToString() { return "GameObject"; }

        // Accessors
        public int GetId() { return m_Id; }
        public string GetName() { return m_Name; }
        public string GetTag() { return m_Tag; }
        public bool GetTransparent() { return m_Transparent; }
        public bool GetDynamic() { return m_Dynamic; }

        // Mutators
        public void SetId(int id) { m_Id = id; }
        public void SetName(string name) { m_Name = name; }
        public void SetTag(string tag) { m_Tag = tag; }
        public void SetTransparent(bool transparent) { m_Transparent = transparent; }
        public void SetDynamic(bool dynamic) { m_Dynamic = dynamic; }
    }
}
