if (typeof firebase === 'undefined') throw new Error('hosting/init-error: Firebase SDK not detected. You must include it before /__/firebase/init.js')
;
var firebaseConfig = {
  "projectId": "gpstrackingapi",
  "appId": "1:849272530588:web:2bf5bdc9ed399e2dffef59",
  "databaseURL": "https://gpstrackingapi-default-rtdb.firebaseio.com",
  "apiKey": "AIzaSyB0NY4Q7L1Xf4VtpmH5xkfMXDhPrODPivg",
  "authDomain": "gpstrackingapi.firebaseapp.com"
};

if (firebaseConfig) {
  firebase.initializeApp(firebaseConfig);
}
