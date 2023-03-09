const express = require('express')
const firebase = require('firebase')
const config = require('./config')
const auth = require('./auth')

const port = 80
const fb = firebase.initializeApp(config)
let authed = false

function getTimestamp(){
	return Math.floor(new Date())
}

function authSystem(){
	fb.auth().signInWithEmailAndPassword(auth.email, auth.password).then( e => {
		authed = true
	}).finally( e => {} )
}

function gps(req, res){
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
		if(!authed){
			authSystem()
		}

		let data = req.query
		let id = req.query.id
		let ref = fb.database().ref(id)
		let logRef = fb.database().ref("TrackerLog").child(id)
		let timestamp = getTimestamp()
		delete data.id

		console.table(req.query)
		data.timestamp = timestamp

		ref.child("currentTrackerData").set(data)
		logRef.child(timestamp.toString()).set(data)
		res.end()
	}catch(e){
		console.log(e)
		res.end()
	}
}

app = express()
app.use(express.static("public"))
app.get("/api", api)
app.get("/gps", gps)
authSystem()

app.listen(port, () => {
	console.log(`[SERVER-ONLINE] ::${port}`);
})
