const express = require("express")
const fb = require("./fb")
const SENSOR_ID = "BIN-SENSOR-11223344"

const port = process.env.PORT
const app = express()
fb.auth()

let stateValue = 0
let channelValue1 = 0

function getData(req, res){
	try{
		stateValue = parseInt(req.query.value)
		console.log(`[+] DATA RECV: ${stateValue}`)
		fb.auth()
		fb.database().ref(`/${SENSOR_ID}/currentReading`).set(stateValue)
		fb.database().ref(`/${SENSOR_ID}/rawSensorDataLog/${Math.floor(new Date()/1000)}`).set(stateValue)
		res.send("")
	}catch(e){
		console.log(e)
	}
}

function channel1(req, res){
        try{
                channelValue1 = parseInt(req.query.value)
                console.log(`[+] Channel-1 DATA RECV: ${channelValue1}`)
                res.send("")
        }catch(e){
                console.log(e)
        }
}



function sendData(req, res){
	console.log("[+] STATE VALUE SENT")
	res.send(stateValue.toString())
}

function sendData1(req, res){
        console.log("[+] Channel-1 STATE VALUE SENT")
        res.send(channelValue1.toString())
}

app.get("/api-1", channel1)
app.get("/data-1", sendData1)

app.get("/api", getData)
app.get("/data", sendData)
app.listen(port, () => { console.log(`[+] Server ONLINE: ${port}`) })
