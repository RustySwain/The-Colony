using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class AudioSource
    {
        private string m_Sound;
        private bool m_added;

        public override string ToString() { return "AudioSource"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public string GetSound() { return m_Sound; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetSound(string sound) { m_Sound = sound; }
    }
}
