// HomePage.js
import React, { useState, useEffect } from 'react'
import { StyleSheet, View, Text, Image, Button } from 'react-native'
import { db } from "./firebaseConfig.js"
import { getDoc, doc, onSnapshot } from "firebase/firestore"


function formattedTime(milliseconds) {
  seconds = Math.floor(milliseconds/1000)
  minutes = Math.floor(seconds/60)
  hours = Math.floor(minutes/60)
  seconds %= 60
  minutes %= 60
  return (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes) + ":" + (seconds < 10 ? "0" : "") + String(seconds)
}

const HomePage = ({ navigation }) => {
  const [countDown, setCountDown] = useState(0)
  const [showDispenserPageBtn, setShowDispenserPageBtn] = useState(0)

  async function fetchTime() {
    const docSnap = await getDoc(doc(db, "users", "DA151F76"))
    if (docSnap.exists()) {
      const time = docSnap.data().time
      return time
    }
  }
  
  useEffect(async () => {
    let time = await fetchTime()

    const unsub = onSnapshot(doc(db, "users", "DA151F76"), (doc) =>{
      time = doc.data().time
      console.log("Current data: ", time)
      navigation.navigate('HomePage')
      console.log("Home")
    })

    const interval = setInterval(async () => {
      const timeLeft = time + 24*60*60*1000 - Date.now()
      if (timeLeft > 0) {
        setShowDispenserPageBtn(false)
        setCountDown(timeLeft)  
      }
      else {
        setShowDispenserPageBtn(true)
      }
    }, 1000)

    return () => {
      clearInterval(interval)
      unsub()
    }
  }, [])

  return (
    <View style={styles.container}>
      <Image
        source={require('./img/medicare-removebg.png')}
        style={styles.homeImage}
        resizeMode="contain"
      />
      <Text style={styles.helloText}>Hei Albert</Text>
      { !showDispenserPageBtn
        ?
        <>
          <Text style={styles.drugDropTimeText}>New drug drop in</Text>
          <Text style={styles.drugDropTime}>{formattedTime(countDown)}</Text>
        </>
        :
        <></>
      }
      { showDispenserPageBtn
        ?
        <Button
          title="Hent ut medikamenter"
          onPress={() => {
            navigation.navigate('DispenserPage')
          }}
        />
        :
        <></>
      }
    </View>
  )
}


const styles = StyleSheet.create({
  container: {
    // backgroundColor: 'blue'
  },

  homeImage: {
    width: '100%',
  },

  helloText: {
    textAlign: 'center',
    fontSize: 50,
    paddingBottom: 20
  },

  drugDropTimeText: {
    textAlign: 'center',
    fontSize: 30
  },

  drugDropTime: {
    textAlign: 'center',
    fontSize: 30
  }
})

export default HomePage