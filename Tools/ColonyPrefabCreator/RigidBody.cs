using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class RigidBody
    {
        private const int Id = 2;
        private bool m_added;

        public override string ToString() { return "RigidBody"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public int GetId() { return Id; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
    }
}
