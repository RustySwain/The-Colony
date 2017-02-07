using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class Animator
    {
        private const int Id = 10;
        private bool m_added;
        private List<string> m_animations = new List<string>();

        public override string ToString() { return "Animator"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public int GetId() { return Id; }
        public List<string> GetAnimations() { return m_animations; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void AddAnimation(string file) { m_animations.Add(file); }
    }
}
