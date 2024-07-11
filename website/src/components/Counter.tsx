import { createSignal } from "solid-js"

function CounterButton() {
  const [count, setCount] = createSignal(0)

  const increment = () => setCount(count() + 1)

  return (
    <div class="flex gap-4 items-center">
      <button onClick={increment} class="px-3 py-1 border border-black/25 dark:border-white/25 hover:bg-black/5 dark:hover:bg-white/15 blend">
        Increment
      </button>
      <div>
       Clicked {count()} {count() === 1 ? "time" : "times"}
      </div>
    </div>

  )
}

export default CounterButton
