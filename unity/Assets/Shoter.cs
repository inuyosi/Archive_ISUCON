using UnityEngine;
using System.Collections;

public class Shoter : MonoBehaviour {
	int count=0;
	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {

		//左クリックがおされたら 
		if(Input.GetMouseButtonDown(0))
		{
			
			GameObject prefab = null;
			//座標の変換.
			Vector3 create_shoter_vec = new Vector3(
				4.206501f,
				-6.226032f,
				-0.3553429f
				);
			
			// Objectsフォルダ内のBallオブジェクトを参照 
			prefab = (GameObject)Resources.Load ("Objects/Ball");
			
			if(prefab != null){
				
				// オブジェクト生成 
				GameObject ini_ball =
					(GameObject) GameObject.Instantiate(prefab,
					                                    create_shoter_vec, Quaternion.identity);
				
				
				Vector3 ball_vec = new Vector3(
					0.0f,
					20.0f,
					0.0f
					);
				
				// ボール生成時に速度を持たせる 
				ini_ball.GetComponent<Rigidbody>().velocity = ball_vec;

				if(count >= 100){
					Application.LoadLevel("ballgame");
				}	

				count += 1;
				print (count);
			}
		}
		
	}
}
