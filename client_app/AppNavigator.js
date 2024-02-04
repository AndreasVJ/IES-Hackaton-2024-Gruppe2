// AppNavigator.js
import { StatusBar } from 'expo-status-bar'
import { NavigationContainer } from '@react-navigation/native'
import { createStackNavigator } from '@react-navigation/stack'
import HomePage from './HomePage'
import DispenserPage from './DispenserPage'

const Stack = createStackNavigator()

const AppNavigator = () => {
  return (
    <NavigationContainer>
      <StatusBar />
      <Stack.Navigator initialRouteName="HomePage">
        <Stack.Screen name="HomePage" component={HomePage} />
        <Stack.Screen name="DispenserPage" component={DispenserPage} />
      </Stack.Navigator>
    </NavigationContainer>
  )
}

export default AppNavigator