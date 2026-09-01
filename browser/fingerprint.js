// Anti-fingerprinting layer
const TorFingerprint = {
  spoofCanvas: function() {
    const originalToDataURL = HTMLCanvasElement.prototype.toDataURL;
    HTMLCanvasElement.prototype.toDataURL = function() {
      const context = this.getContext('2d');
      const noise = Math.random() * 0.001;
      const imageData = context.getImageData(0, 0, this.width, this.height);
      for (let i = 0; i < imageData.data.length; i += 4) {
        imageData.data[i] += noise;
      }
      context.putImageData(imageData, 0, 0);
      return originalToDataURL.apply(this, arguments);
    };
  },

  spoofWebGL: function() {
    const getParameter = WebGLRenderingContext.prototype.getParameter;
    WebGLRenderingContext.prototype.getParameter = function(param) {
      if (param === this.RENDERER || param === this.VENDOR) {
        return 'Generic WebGL Renderer';
      }
      return getParameter.apply(this, arguments);
    };
  },

  spoofTimezone: function() {
    Date.prototype.getTimezoneOffset = function() { return 0; };
  }
};

TorFingerprint.spoofCanvas();
TorFingerprint.spoofWebGL();
TorFingerprint.spoofTimezone();