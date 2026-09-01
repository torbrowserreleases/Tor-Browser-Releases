// NoScript integration for Tor Browser
const NoScriptTor = {
  securityLevels: {
    STANDARD: 0,
    SAFER: 1,
    SAFEST: 2
  },

  currentLevel: 0,

  applyLevel: function(level) {
    this.currentLevel = level;
    
    switch(level) {
      case this.securityLevels.SAFER:
        this.disableJavaScriptOnHTTP();
        this.disableMediaCodecs();
        break;
      case this.securityLevels.SAFEST:
        this.disableAllJavaScript();
        this.disableAllMedia();
        this.disableFonts();
        break;
    }
  },

  disableJavaScriptOnHTTP: function() {
    if (location.protocol === 'http:') {
      document.querySelectorAll('script').forEach(s => s.remove());
    }
  },

  disableAllJavaScript: function() {
    document.querySelectorAll('script').forEach(s => s.remove());
  },

  disableMediaCodecs: function() {
    HTMLMediaElement.prototype.play = function() { return Promise.reject(); };
  }
};

NoScriptTor.applyLevel(NoScriptTor.securityLevels.STANDARD);