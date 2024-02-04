import { initializeApp } from "firebase/app"
import { getFirestore } from "firebase/firestore"

const firebaseConfig = {
  apiKey: "AIzaSyBMdIr9yelGR95c8WQnh93mpVvEY9NRrss",
  authDomain: "ies-hackaton-2024-gruppe2.firebaseapp.com",
  projectId: "ies-hackaton-2024-gruppe2",
  storageBucket: "ies-hackaton-2024-gruppe2.appspot.com",
  messagingSenderId: "733594890685",
  appId: "1:733594890685:web:98f8b452dfbc127ae762d4"
}

const app = initializeApp(firebaseConfig)
const db = getFirestore(app)

export { db }