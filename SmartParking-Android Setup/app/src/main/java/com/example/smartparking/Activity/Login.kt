package com.example.smartparking.Activity

import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*
import com.example.smartparking.R
import com.google.firebase.auth.FirebaseAuth

class Login : AppCompatActivity() {
    lateinit var email: EditText
    lateinit var password: EditText
    lateinit var login: ImageButton
    lateinit var signup: TextView
    private var mAuth: FirebaseAuth ?= null
    var userName: String? = null
    var userPassword: String? = null
    lateinit var sharedPreferences: SharedPreferences
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        sharedPreferences =
            getSharedPreferences(getString(R.string.preference_file_name), Context.MODE_PRIVATE)
        if (intent != null) {
            val i = intent.getStringExtra("logout")
            if (i == "a") {
                editPreferences()
            }
        }
        val isLoggedIn = sharedPreferences.getBoolean("isLoggedIn", false)
        setContentView(R.layout.activity_login)
        if (isLoggedIn) {
            val i = Intent(this@Login, Home::class.java)
            startActivity(i)
            finish()
        }
        email = findViewById(R.id.email)
        password = findViewById(R.id.password)
        login = findViewById(R.id.login)
        signup = findViewById(R.id.signup)
        mAuth = FirebaseAuth.getInstance()

        login.setOnClickListener {
            userName = email.getText().toString().trim { it <= ' ' }
            userPassword = password.getText().toString().trim { it <= ' ' }
            if (userName!!.isEmpty()) {
                Toast.makeText(this@Login, "Please enter Email ID", Toast.LENGTH_SHORT)
                    .show()
            } else if (userPassword!!.isEmpty()) {
                Toast.makeText(this@Login, "Please enter Password", Toast.LENGTH_SHORT)
                    .show()
            } else {
                next()
            }
        }
        signup.setOnClickListener {
            val intent = Intent(this@Login,SignUp::class.java)
            startActivity(intent)
        }
    }
    private operator fun next() {
        mAuth!!.signInWithEmailAndPassword(userName!!, userPassword!!).addOnCompleteListener(
            this@Login
        ) { task ->
            if (task.isSuccessful) {
                Toast.makeText(this@Login, "Logged in Successfully !", Toast.LENGTH_SHORT)
                    .show()
                savePreferences()
                val intent = Intent(this@Login, Home::class.java)
                startActivity(intent)
            } else {
                Toast.makeText(this@Login, "Invalid Credentials !", Toast.LENGTH_SHORT)
                    .show()
            }
        }
    }

    fun savePreferences() {
        sharedPreferences.edit().putBoolean("isLoggedIn", true).apply()
    }

    fun editPreferences() {
        sharedPreferences.edit().putBoolean("isLoggedIn", false).apply()
    }
}