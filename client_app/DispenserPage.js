// Screen2.js
import React, { useState } from 'react'
import { View, Text, Button, ActivityIndicator } from 'react-native'

const DispenserPage = ({ navigation }) => {
  const [isElementVisible, setIsElementVisible] = useState(true);

  const toggleVisibility = () => {
    setIsElementVisible(!isElementVisible);
  };


  return (
    <View>
      <Text>DispenserPage</Text>
      <Button
        title="Activate dispenser"
        onPress={() => console.log("dispensing")}
      />
      <ActivityIndicator size={"large"}/>
    </View>
  )
}


export default DispenserPage