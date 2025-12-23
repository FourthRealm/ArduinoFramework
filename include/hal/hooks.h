#ifndef HOOKS_H
#define HOOKS_H

namespace fw::hal {

void onTimer0Overflow();
void onTimer1Overflow();
void onTimer2Overflow();

} // namespace fw::hal

#endif // HOOKS_H