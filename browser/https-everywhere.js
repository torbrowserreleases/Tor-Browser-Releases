// HTTPS Everywhere integration
const HTTPSEverywhere = {
  rules: new Map(),

  shouldUpgrade: function(url) {
    const hostname = new URL(url).hostname;
    return this.rules.has(hostname) && url.startsWith('http://');
  },

  upgrade: function(url) {
    if (this.shouldUpgrade(url)) {
      return url.replace('http://', 'https://');
    }
    return url;
  },

  loadRules: function(rulesets) {
    rulesets.forEach(rule => {
      this.rules.set(rule.hostname, rule.pattern);
    });
  }
};

// Intercept navigation
const originalFetch = window.fetch;
window.fetch = function(url, options) {
  const upgradedURL = HTTPSEverywhere.upgrade(url);
  return originalFetch(upgradedURL, options);
};