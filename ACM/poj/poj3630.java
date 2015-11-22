package Main;
import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.lang.Math;
class Node{
	int num,id;
	Node[] ch;
}
public class Main {
	static final int sigma_size = 10;
	static final int MAXN = 5000000;
	//static StreamTokenizer cin=new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
	//static PrintWriter cout=new PrintWriter(new OutputStreamWriter(System.out));
	static int cnt,flag;
	static Node root;
	static Node[] node = new Node[MAXN];
	public static class Trie{
		public void init(){
			cnt = 0;
			root = newnode();
		}
		public Node newnode(){
			node[cnt] = new Node();
			node[cnt].id = cnt; node[cnt].num = 0;
			node[cnt].ch = new Node[sigma_size];
			return  node[cnt++];
		}
		public void insert(String s){
			int len = s.length();
			Node p = root;
			for(int i = 0;i < len;i++){
				int k = s.charAt(i)-'0';
				if(p.ch[k] == null)
					p.ch[k] = newnode();
				if(p.num > 0)
					flag=1;
				p = p.ch[k];
			}
			p.num++;
			for(int i = 0;i < sigma_size;i++){
				if(p.ch[i] != null){
					flag = 1;
					break;
				}
			}
		}
	}
	static Trie trie = new Trie();
	public static  void main(String[] args) throws IOException {
			//final FileInputStream in = new FileInputStream("/home/mashiro/in.txt");
			final Scanner cin = new Scanner(System.in);
			int T = cin.nextInt();
			while(T-- > 0){
				int n = cin.nextInt();
				trie.init(); flag = 0;
				for(int i=0;i<n;i++){
					String s = cin.next();
					//System.out.println(s);
					if(flag == 0)
						trie.insert(s);
				}
				if(flag > 0)
					System.out.println("NO");
				else 
					System.out.println("YES");
			}
			
	}
}