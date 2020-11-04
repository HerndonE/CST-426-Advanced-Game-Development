using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public	class EventBus :	MonoBehaviour	{	

	private	Queue<GameEvent>	_events;	
	public	event	Action<GameEvent>	OnGameEvent;	
	public	void	AddEvent	(GameObject sender, string message)	{	
		GameEvent evt	=	new	GameEvent(sender,message);	
		_events.Enqueue(evt);	
	}	
	public void Start(){
		_events = new Queue<GameEvent> ();
	}
	public	void	Update	()	{	
		while	(_events.Count	>	0)	{	
			GameEvent evt	=	_events.Dequeue();	
			OnGameEvent(evt);	
		}	
	}	
}	