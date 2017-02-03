using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ColonyPrefabManager
{
    class AudioSource
    {
        private string m_Clip = "";
        private bool m_added;

        public override string ToString() { return "AudioSource"; }

        // Accessors
        public bool GetAdded() { return m_added; }
        public string GetClip() { return m_Clip; }

        // Mutators
        public void SetAdded(bool added) { m_added = added; }
        public void SetClip(string clip) { m_Clip = clip; }
    }
}
