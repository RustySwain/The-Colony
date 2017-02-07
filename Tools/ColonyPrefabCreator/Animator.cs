using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Animator
    {
        private const int Id = 1;
        private bool m_added;

        public override string ToString() { return "Animator"; }

        // Accessors
        public bool GetAdded() { return m_added; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
    }
}
