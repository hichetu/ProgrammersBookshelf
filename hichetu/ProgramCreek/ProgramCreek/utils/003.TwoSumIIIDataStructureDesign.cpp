/*

public class TwoSum {
	private HashMap<Integer, Integer> elements = new HashMap<Integer,
		Integer>();
	public void add(int number) {
		if (elements.containsKey(number)) {
			elements.put(number, elements.get(number) + 1);
		}
		else {
			elements.put(number, 1);
		}
	}
	public boolean find(int value) {
		for (Integer i : elements.keySet()) {
			int target = value - i;
			if (elements.containsKey(target)) {
				if (i == target && elements.get(target) < 2) {
					continue;
				}
				return true;
			}
		}
		return false;
	}
}

*/

