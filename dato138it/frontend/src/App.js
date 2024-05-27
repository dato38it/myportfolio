import logo from './logo.svg';
import './App.css';
import Nav from './components/Nav'
import { useRef, useEffect, useState } from 'react'
function App() {
	const [place, setPlace] = useState([])
	useEffect(() => {
		getData()
	}, [])
	const homeRef = useRef(null)
	const placeRef = useRef(null)
	const getData = async () => {
		const placeResponse = await fetch('/place')
		const placeData = await placeResponse.json()
		setPlace(placeData)
	}
	return (
  	<>
    <Nav homeRef={homeRef} placeRef={placeRef} />
		<div className='md:h-full pt-10' ref={homeRef}>
			<div className='md:w-2/4 w-10/12 mx-auto mt-10 mb-3'>
				<h1 className='text-5xl mb-3'>Engineer</h1>
			</div>
			<div className='flex md:flex-row flex-col space-between md:w-2/4 m-auto py-5 border rounded-sm px-3 shadow'>
				<div>
					<ul>
                            			<li><p className='pt-3'><strong>Давид:</strong> 31 год;</p></li>
						<li><p className='pt-3'><strong>Навыки:</strong> Html, Linux, Windows, Виртуализация, Bash, Lamp, Nginx, Sql, English, Python, Etl-процессы, Dwh, AntiFraud, Облачные сервисы, Git, Docker;</p></li>
						<li><p className='pt-3'><strong>Обратная связь:</strong> dato38it@yandex.ru; telegram - @dato38it; https://github.com/dato38it;</p></li>
                            			<li><p className='pt-3'><strong>О себе:</strong> Я являюсь специалистом в области информационных технологии IT с более 5 летним опытом работы в администрировании серверов различных ОС, в написании простых скриптов и в виртуализации. В текущем месте работы внедряю специальные программные обеспечения, ввожу в эксплуатацию технику - принтеры, сканеры, компьютеры и администрирую сервера на windows. Для саморазвития я отдельно свободно читаю и перевожу техническую документацию на английском языке, программирую на Python и разрабатываю свой сайт-портфолио, используя такие инструменты, как облачные сервисы, контейнеры, python и sql запросы. Имеются свои проекты в github. Мне интересно работать в команде, активно развиваться и изучать новые технологии и инструменты.</p></li>
                        		</ul>
				</div>
			</div>
		</div>
		<div className='md:h-full pt-16' ref={placeRef}>
			<div className='mb-5 mx-5'>
				<h1 className='text-5xl mb-3'>My Work Experience</h1>
			</div>
			<div className='grid md:grid-cols-2 grid-cols-1 gap-4 mx-5'>
			{place && place.map(e => (
				<div key={e.id} className='border rounded-sm p-3 shadow'>
					<h5 className='text-2xl text-cyan-900 border-b-2 border-slate-300'>{e.begin} - {e.finish}: {e.spec}</h5>
					<p className='pt-3'>{e.title}; <strong>Дополнительная информация: </strong>{e.description} <strong>Достижения: </strong>{e.progress} </p>
				</div>
			))}
			</div>
		</div>
	</>
  	);
}
export default App;
