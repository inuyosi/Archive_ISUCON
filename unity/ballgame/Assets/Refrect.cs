using UnityEngine;
using System.Collections;

public class Refrect : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	


	void OnTriggerEnter(Collider col_obj) {
		
		// ボールとの判定を取ります
	//	if(col_obj.gameObject.tag == "Ball") {
			
			GameObject o = col_obj.gameObject;
			// 反射した時のボールのベクトル 
			Vector3 ball_vec = new Vector3(
				0.0f,
				Random.Range(15.0f, 25.0f),
				0.0f
				);
			
			// ボール生成時に速度を持たせる 
			o.GetComponent<Rigidbody>().velocity = ball_vec;
			
	//	}
		
	}
}
