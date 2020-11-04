using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public	class	GameEvent	{	
	public GameObject sender;
	public string message;
	public GameEvent (GameObject sender, string message){
		this.sender = sender;
		this.message = message;
	}
}	
