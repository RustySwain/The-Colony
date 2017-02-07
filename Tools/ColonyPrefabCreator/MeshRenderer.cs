using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class MeshRenderer
    {
        private const int Id = 6;
        private bool m_added;
        private string m_Mesh;

        public override string ToString() { return "MeshRenderer"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public int GetId() { return Id; }
        public string GetMesh() { return m_Mesh; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetMesh(string mesh) { m_Mesh = mesh; }
    }
}
