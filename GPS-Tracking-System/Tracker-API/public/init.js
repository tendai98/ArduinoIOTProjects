if (typeof firebase === 'undefined') throw new Error('hosting/init-error: Firebase SDK not detected. You must include it before /__/firebase/init.js')
;

var firebaseConfig = {

	"apiKey" : "AIzaSyCJLz86jXJKRCKxpVnvxnL8qrQUntCd9vQ",
	"appId" : "1:542543035627:web:b8f3a60705bea0759f92ae",
	"authDomain" : "tracking-monitoring-system.firebaseapp.com",
	"projectId" : "tracking-monitoring-system",

};

if (firebaseConfig) {
  firebase.initializeApp(firebaseConfig);
}
