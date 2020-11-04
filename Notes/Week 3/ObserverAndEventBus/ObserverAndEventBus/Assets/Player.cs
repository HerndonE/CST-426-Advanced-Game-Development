using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Player : MonoBehaviour {
	public double health = 0;

	// Declare an event for users to add their listeners to
	public event Action OnHealthUpdate;

	public void	UpdateHealth	(double health)	{	
		this.health	+= health;		
		OnHealthUpdate();	
	}	

	double oldPositionX = 0;

	public void Update() {
		if (transform.position.x != oldPositionX) {
			UpdateHealth (Math.Abs (transform.position.x));
		}
		oldPositionX = transform.position.x;
	}
}
