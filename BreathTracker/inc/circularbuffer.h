#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <QObject>
#include <mutex>
#include <stddef.h>
#include <vector>

/* TODO:
 *
 * 1. Add clearing of Buffer
 * 2. Add read all()
 * 3. Possibly move Buffer Subscription into Bufer Class
 *
 */

class CircularBuffer : public QObject {
  Q_OBJECT
public:
  explicit CircularBuffer(size_t capacity, int newDataIntervalMS = 1000,
                          QObject *parent = nullptr);
  ~CircularBuffer();

  // writing new data to the buffer
  void writeNewItem(const double &newItem);

  /** Reading out a range of the latest data
   *
   *  subscriber: Averager, Trends
   *  */

  std::vector<double> readLastNValues(size_t n);
  std::vector<double> readAllValues();

  bool isEmpty();
  bool isFull();
  size_t getBufferSize();
  size_t getBufferCapacity();

  void clear();

  signals:

  void dataAdded(int newDataIntervalMs);

private:
  // Buffer holding any item
  std::vector<double> _buffer;
  int _newDataIntervalMS;
  // index pointer
  size_t _start;
  size_t _end;
  size_t _capacity;
  size_t _size;
  mutable std::mutex _mtx; // probably not necessary

  // readIndex not as member variable for statelessness
};

#endif // CIRCULARBUFFER_H
