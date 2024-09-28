namespace Vishal {
	class Test
	{
	public:
		Test();
		void f1();
		void f2(int j);
		//void f2(const int j);	// overloading ambiguous with void f2(int j);
        //void f2(int &j);		// overloading ambiguous with void f2(int j);
		//void f2(const int &j); // overloading ambiguous with void f2(int j);
		void f2(int i) const;
    private:
        int i;
	};
}