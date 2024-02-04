import React, { useState } from 'react'
import { StyleSheet, View, Text, Button } from 'react-native'
import AnimatedLoader from 'react-native-animated-loader'

const DispenserPage = ({ navigation }) => {
  const [isLoading, setIsLoading] = useState(false)

  return (
    <View style={styles.container}>
      { isLoading ?
        <AnimatedLoader
          visible={true}
          overlayColor="rgba(255,255,255,1)"
          source={require("./Animation.json")}
          animationStyle={styles.lottie}
          speed={1}>
          <Text style={styles.infoText}>Hold mobilen nær automaten</Text>
          {/* <Button 
          title='Avbryt'
          onPress={setIsLoading(false)}
          /> */}
        </AnimatedLoader>
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

  lottie: {
    width: 400,
    height: 400,
  },

  infoText: {
    fontSize: 20
  }
})


export default DispenserPage