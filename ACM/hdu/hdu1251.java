/* ********************************************************
  file name: hdu1251.java
  author : Sakura_Mashiro
  create time:  2015年11月21日 星期六 18时30分58秒
*********************************************************/
//package Main;
import java.io.*;
import java.util.*;
import java.math.BigInteger;
import java.lang.Math;
class Node{
	int id,num;
	Node[] ch;
}
public class Main {
	static final int sigma_size = 26;
	static final int MAXN = 400000;
	//static StreamTokenizer cin=new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
	//static PrintWriter cout=new PrintWriter(new OutputStreamWriter(System.out));
	static int cnt;
	static Node root;
	static Node[ ]  node = new Node[MAXN];
	public static class Trie{
		public  void init(){
			cnt = 0;
			root = newnode();
		}
		public Node newnode(){
			node[cnt] = new Node();
			node[cnt].id = cnt; node[cnt].num = 0;
			node[cnt].ch = new Node[sigma_size];
			return  node[cnt++];
		}
		public  void insert(String s){
			int len = s.length();
			Node p = root;
			for(int i = 0;i < len;i++){
				int k = s.charAt(i)-'a';
				if(p.ch[k] == null){
					p.ch[k] = newnode();
				}
				p.ch[k].num++;
				p = p.ch[k];
			}
		}
		public int query(String s){
			int len = s.length();
			Node p = root;
			for(int i = 0;i < len;i++){
				int k = s.charAt(i)-'a';
				if(p.ch[k] == null)
					return 0;
				p = p.ch[k];
			}
			return p.num;
		}
	}
	static Trie trie = new Trie();
	public static  void main(String[] args) throws IOException {
			//final FileInputStream in = new FileInputStream("/home/mashiro/in.txt");
			final Scanner cin = new Scanner(System.in);
			trie.init();
			while(cin.hasNext()){
				String s;
				s = cin.nextLine();
				if (s.equals(""))
					break;
				trie.insert(s);
				
			}
			while(cin.hasNext()){
				String s = cin.nextLine();
				int ans = trie.query(s);
				System.out.println(ans);
			}
	}
}
