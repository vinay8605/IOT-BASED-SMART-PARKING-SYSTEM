package com.example.smartparking.Activity

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageButton
import com.example.smartparking.R

class MainActivity : AppCompatActivity() {
    lateinit var splash: ImageButton
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        splash = findViewById(R.id.splash)
        splash.setOnClickListener {
            val i = Intent(this, Login::class.java)
            startActivity(i)
        }
    }
}