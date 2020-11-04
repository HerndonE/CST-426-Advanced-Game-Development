using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBehaviour : MonoBehaviour {
	private Transform player;
	private EventBus eventBus;
	// Use this for initialization
	void Start () {
		player = GameObject.Find ("Player").transform;
		eventBus = GameObject.Find ("EventSystem").GetComponent<EventBus> ();
		eventBus.OnGameEvent += HandleOnGameEvent;
	}

	public void HandleOnGameEvent(GameEvent e){
		Debug.Log (e.sender.name + " says: " + e.message);
	}
	// Update is called once per frame
	void Update () {
		if ((transform.position - player.transform.position).magnitude < 2)
			eventBus.AddEvent (gameObject, "Player near me!");
			
	}
}
