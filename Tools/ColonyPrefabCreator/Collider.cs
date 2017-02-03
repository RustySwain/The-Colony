using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Collider
    {
        private const int Id = 3;
        private bool m_added;

        public override string ToString() { return "Collider"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public int GetId() { return Id; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
    }
}
