using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour {
	public Player player;
	public Text   uiText;

	public	void Start()	{	
		player = GameObject.Find ("Player").GetComponent<Player> ();	
		uiText = GameObject.Find ("Text").GetComponent<Text> ();
		player.OnHealthUpdate += UpdateUI;	
	}	

	private	void UpdateUI()	{	
		uiText.text = player.health.ToString();
	}
}
