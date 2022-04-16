import java.util.List;
import java.util.ArrayList;

public class Sort {
	
	//Add your method here.
	public static void selectionSort(List<Integer> list){
		int i;
		int j;
		//System.out.println("List size="+list.size());
		for (i = 0; i < list.size(); i++){
			int min = i;
			//System.out.println("i="+i);
			for (j = i+1; j < list.size(); j++){
				//System.out.println("j="+j);
				//System.out.println("min="+min);
				if (list.get(j)<list.get(min)){
					min = j;
				}
			}
			if (min != i){
				int temp = list.get(i);
				list.set(i, list.get(min));
				list.set(min, temp);
			}
		}

	}
	
	public static void main(String[] args) {
		//Sort it out.
		ArrayList<Integer> mylist = new ArrayList<Integer>();
		mylist.add(5);
		mylist.add(3);
		mylist.add(8);
		mylist.add(1);
		mylist.add(2);
		mylist.add(9);
		System.out.println("Before:");
		for (int i : mylist){
			System.out.println(i);
		}
		selectionSort(mylist);
		System.out.println("After:");
		for (int i : mylist){
			System.out.println(i);
		}
	}
	
}
