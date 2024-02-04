// Screen2.js
import React, { useState } from 'react'
import { StyleSheet, View, Text, Button, ActivityIndicator } from 'react-native'

const DispenserPage = ({ navigation }) => {
  const [isLoading, setIsLoading] = useState(false)


  return (
    <View style={styles.container}>
      { isLoading ?
        <>
          <Text>Hold mobilen nær automaten</Text>
          <ActivityIndicator size={"large"}/>
        </>
        :
        <Button
          title="Activate dispenser"
          onPress={() => setIsLoading(true)}
        />

      }
    </View>
  )
}


const styles = StyleSheet.create({
  container: {
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center'
  },
})


export default DispenserPage