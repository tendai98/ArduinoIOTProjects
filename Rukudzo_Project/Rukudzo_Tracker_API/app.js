const express = require('express')
const firebase = require('firebase')
const config = require('./config')
const auth = require('./auth')

const port = process.env.PORT || 5000
const fb = firebase.initializeApp(config)
let authed = false


function timestampStr(){
	return Math.floor(new Date())+""
}

function authSystem(){
	fb.auth().signInWithEmailAndPassword(auth.email, auth.password).then( e => {
		authed = true
	}).finally( e => {} )
}

function data(req, res){
	try{
		let ref = fb.database().ref(req.query.id)
		let target = ref.child(req.query.target)

		target.on("value", data => {
			res.json(data.val())
		})
	}catch(e){
			res.json({code:-1})
	}
}


function api(req, res){

	try{
		let ref = fb.database().ref(req.query.id)
		
		let info = {
			bpm: req.query.bpm,
			ox2: req.query.ox2,
			lat: req.query.latitude, 
			lon: req.query.longitude
		}

		ref.child("currentData").set(info)
		ref.child("dataLog").child(timestampStr()).set(info)
		res.json({code: 0})
	}catch(e){
		res.json({code: -1})
	}
}

app = express()
app.use(express.static("public"))
app.get("/api", api)
app.get("/data", data)
authSystem()

app.listen(port, () => {
	console.log(`::${port}`);
})
