/*
 * Singleton.h
 *
 *  Created on: 23.10.2017
 *      Author: skrec
 */

#ifndef SOQOSMW_BASE_SINGLETON_H_
#define SOQOSMW_BASE_SINGLETON_H_

template <typename C> class Singleton
 {
 public:
    static C* instance ()
    {
       if (!_instance)
          _instance = new C ();
       return _instance;
    }
    virtual
    ~Singleton ()
    {
       _instance = 0;
    }
 private:
    static C* _instance;
 protected:
    Singleton () { }
 };
 template <typename C> C* Singleton <C>::_instance = 0;


/* Usage */
// class Test : public Singleton <Test>
// {
// friend class Singleton <Test>;
// public:
//    ~Test () { }
//    void xyz () { }
// protected:
//    Test () { }
// };
// Test::instance ()->xyz ();



#endif /* SOQOSMW_BASE_SINGLETON_H_ */
