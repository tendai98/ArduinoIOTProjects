const firebase = require("firebase")
const appConfiguration = require("./app.json")
const userConfiguration = require("./user.json")


let authEnabled = false

firebase.initializeApp(appConfiguration)

function authApp(){
	if(!authEnabled){
		firebase.auth().signInWithEmailAndPassword(userConfiguration.email, userConfiguration.password).then( p => {
			authEnabled = true
			console.log("Authed!")
		}).catch( e => {
			console.log(e)
		})
	}
}

module.exports = {
	auth: authApp,
	database:firebase.database
}


